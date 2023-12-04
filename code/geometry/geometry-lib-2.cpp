/* GEOMETRY ===================================== */
const double PI = acos(-1.0);
const double EPS = 1e-9;
double toDegrees (double radian) { return 180.0 * radian / PI; }
double toRadian (double degrees) { return degrees * PI / 180.0; }


struct point {
	double x, y;
	point (double _x, double _y) : x(_x), y(_y) {}
	point () : x(0.0), y(0.0) {}
	bool operator == (const point& p) const { return fabs(p.x - x) < EPS && fabs(p.y - y) < EPS; }
	bool operator < (const point& p) const {
		if (fabs(p.x - x) > EPS) return x < p.x;
		if (fabs(p.y - y) > EPS) return y < p.y;
		return false;
	}
};


/* ============================================== */
string to_string (const point& p) { return "(" + to_string(p.x) + ", " + to_string(p.y) + ")"; }
/* ============================================== */

struct line {
	double a, b, c;
	line (double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
	line (point p1, point p2) {
		if (p1.x == p2.x) { a = 1.0; b = 0.0; c = -p1.x; }
		else {
			a = -(p1.y - p2.y) / (p1.x - p2.x);
			b = 1.0;
			c = -(a * p1.x + p1.y);
		}
	}
};

// Line related functions
bool areParallel (const line& l1, const line& l2) {	return fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS; }
bool areSame (const line& l1, const line& l2, const line& l3) { return areParallel(l1, l2) && fabs(l1.c - l2.c) < EPS; }
bool areIntersect (const line& l1, const line& l2, point& p) {
	if (areParallel(l1, l2)) return false;
	p.x = -(l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	if (fabs(l1.b) > EPS) 	p.y = -(l1.a * p.x + l1.c);
	else 					p.y = -(l2.a * p.x + l2.c);
	return true;
}

// vectors
struct vec {
	double x, y;
	vec (double _x, double _y) : x(_x), y(_y) {}
	vec (point p1, point p2) {
		x = p2.x - p1.x;
		y = p2.y - p1.y;
	}
	double len () const { return hypot(x, y); }
	double lenSq () const { return x * x + y * y; }
};

// Functions related to points and vectors
double dist (const point& p1, const point& p2) { return hypot(p1.x - p2.x, p1.y - p2.y); }
point midPoint (const point& p1, const point& p2) { return point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2); }

vec scaleByFactor (const vec& v, double s) { return vec(v.x * s, v.y * s); }
vec scaleToLength (const vec& v, double l) { return scaleByFactor(v, l / v.len()); }
double dot (const vec& a, const vec& b) { return (a.x * b.x + a.y * b.y); }
double cross (const vec& a, const vec& b) { return (a.x * b.y - b.x * a.y); }

point translate (const point& p, const vec& v) { return point(p.x + v.x, p.y + v.y); } 
vec rotate (const vec& v, double deg) {
	double rad = toRadian(deg);
	return vec(v.x * cos(rad) - v.y * sin(rad), v.x * sin(rad) + v.y * cos(rad));
}

point rotateAbout (const point& p, const point& pivot, double deg) {
	double rad = toRadian(deg);
	vec v = rotate(vec(pivot, p), rad);
	return translate(pivot, v);
}

point closestPointOnLine (const point& a, const point& b, const point& p) {
	vec u (a, b);
	vec v (a, p);
	double s = dot(u, v) / u.lenSq();
	return translate(a, scaleByFactor(u, s));
}

double distFromLine (const point& a, const point& b, const point& p) {
	return dist(p, closestPointOnLine(a, b, p));
}

bool collinear (const point& a, const point& b, const point& c) {
	return fabs(cross(vec(a, b), vec(b, c))) < EPS;
}

bool ccw (const point& a, const point& b, const point& c) {
	return cross(vec(a, b), vec(b, c)) > EPS;
}

/* ============================================== */
template<typename T>
string to_string (vector<T> v) {
	string res = "[";
	for (int i = 0; i < (int)v.size() - 1; i++) res += to_string(v[i]) + ", ";
	if (!v.empty()) res += to_string(v.back());
	res += "]";
	return res;
}
/* ============================================== */
/* ACW angle between u -> v */
double angle (const vec& u, const vec& v) {
	double rad = acos(dot(u, v) / (u.len() * v.len()));
	if (cross(u, v) < -EPS) rad = -rad;
	return rad;
}
/* ============================================== */
double polygonArea (const vector<point> p) {
	double ans = 0.0;
	for (int i = 0; i < (int)p.size() - 1; i++)
		ans += (p[i].x * p[i + 1].y) - (p[i].y * p[i + 1].x);
	return ans / 2.0;
}
bool isOutsidePolygon (vector<point> poly, point p) {
	double windingAngle = 0.0;
	for (int i = 0; i < (int)poly.size() - 1; i++) 
		windingAngle += angle(vec(p, poly[i]), vec(p, poly[i + 1]));
	if (fabs(windingAngle) < EPS) return true;
	return false;
}

vector<point> cutPolygon (vector<point> P, point a, point b) {
	vector<point> R;
	bool lf1, lf2, c1, c2, rt1, rt2;
	for (int i = 0; i < (int)P.size() - 1; i++) {
		
		lf1 = ccw(a, b, P[i]);
		lf2 = ccw(a, b, P[i + 1]);
		c1 = collinear(a, b, P[i]);
		c2 = collinear(a, b, P[i + 1]);
		rt1 = !(lf1 || c1);
		rt2 = !(lf2 || c2);

		if (!rt1) R.push_back(P[i]);
		if ((lf1 && rt2) || (rt1 && lf2)) { /* in -> out OR out -> in*/
			point c;
			areIntersect(line(a, b), line(P[i], P[i + 1]), c);
			R.push_back(c);
		}
	}
	if (R.size() > 1) R.push_back(R.front());
	return R;

}

namespace GrahamScan {
	point pivot;
	bool angleCmp (point& p1, point& p2) {
		if (collinear(pivot, p1, p2)) return dist(p1, pivot) < dist(p2, pivot);
		double angle1 = atan2(p1.y - pivot.y, p1.x - pivot.x);
		double angle2 = atan2(p2.y - pivot.y, p2.x - pivot.x);
		return angle1 < angle2;
	}

	int findLowestPoint (const vector<point>& Q) {
		int ix = 0;
		for (int i = 1; i < (int)Q.size(); i++)
			if ((fabs(Q[i].y - Q[ix].y) < EPS && Q[i].x < Q[ix].x) || Q[i].y < Q[ix].y) ix = i;
		return ix;
	}

	vector<point> CH (vector<point> Q) {
		int n = Q.size();
		if (n <= 3) {
			if (!(Q[0] == Q[n - 1])) Q.push_back(Q[0]);
			return Q;
		}
		// does not handle set of points (n > 3) in which are all collinear
		
		int ix = findLowestPoint(Q);
		swap(Q[ix], Q[0]);
		pivot = Q[0];
		sort(++Q.begin(), Q.end(), angleCmp);
		vector<point> P = {Q[n - 1], Q[0], Q[1]};
		for (int i = 2; i < n; i++) {
			while (!ccw(P[P.size() - 2], P[P.size() - 1], Q[i])) P.pop_back();
			P.push_back(Q[i]);
		}
		return P;
	}

};
/* ============================================== */