/*===================================================================*/
/* Geometry Library */
const double PI = acos(-1.0);
const double EPS = 1e-9;
double toRadians (double deg) { return (PI * deg) / 180.0; }
double toDegrees (double rad) { return (180 * rad) / PI; }


struct point {
	double x, y;
	point (double _x, double _y) : x(_x), y(_y) {}
	point() { point(0, 0); }
	bool operator == (const point& p) const {
		return fabs(this->x - p.x) < EPS && fabs(this->y - p.y) < EPS;
	}

	bool operator < (const point& p) const {
		if (fabs(this->x - p.x) > EPS)
			return this->x < p.x;
		if (fabs(this->y - p.y) > EPS)
			return this->y < p.y;
		return false; /* co-incident points */
	}
};


struct vec {
	double x, y;
	vec (double _x, double _y) : x(_x), y(_y) {}
	vec (point u, point v) : x(v.x - u.x), y(v.y - u.y) {}
	double lenSq () { return x * x + y * y; }
	double len () { return sqrt(this->lenSq()); }
};

struct line {
	double a, b, c;
	line (double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
	line (point p1, point p2) {
		if (fabs(p1.x - p2.x) < EPS) { a = 1; b = 0; c = -p1.x; }
		a = -(p1.y - p2.y) / (p1.x - p2.x);
		b = 1;
		c = -(a * p1.x + p1.y);
	}
};

/* for debugging */
string to_string (point p) { return "(" + to_string(p.x) + ", " + to_string(p.y) + ")"; }
string to_string (line l) { return "(" + to_string(l.a) + ", " + to_string(l.b) + ", " + to_string(l.c) + ")"; }

bool areParallel (line p, line q) { return (fabs(p.a - q.a) < EPS && fabs(p.b - q.b) < EPS); }
bool areIntersect (line l1, line l2, point& res) {
	if (areParallel(l1, l2)) return false;
	res.x = -(l1.b * l2.c - l2.b * l1.c) / (l1.b * l2.a - l2.b * l1.a);
	if (fabs(l1.b) < EPS) res.y = -(l2.a * res.x + l2.c) / l2.b;
	else res.y = -(l1.a * res.x + l1.c) / l1.b;
	return true;
}

vec scaleBy (vec v, double s) { return vec(v.x * s, v.y * s); }
vec scaleTo (vec v, double s) { return scaleBy(v, s / v.len()); }

vec rotate (vec v, double deg) {
	double rad = toRadians(deg);
	return vec(v.x * cos(rad) - v.y * sin(rad),
			   v.x * sin(rad) + v.y * cos(rad));
}
double dot (vec u, vec v) { return u.x * v.x + u.y * v.y; }
double cross (vec u, vec v) { return u.x * v.y - u.y * v.x; }
double projScaleFactor (vec u, vec v) { return dot(u, v) / v.lenSq(); }
vec proj (vec u, vec v) { return scaleTo(v, projScaleFactor(u, v)); }
double angleBetween (vec a, vec b) { return acos(dot(a, b) / (a.len() * b.len())); }

point translate (point p, vec v) { return point(p.x + v.x, p.y + v.y); }

point rotate (point p, double deg) {
	double rad = toRadians(deg);
	return point(p.x * cos(rad) - p.y * sin(rad),
				 p.x * sin(rad) + p.y * cos(rad));
}

point rotateAbout (point p, double deg, point c) {
	vec v (c, {0.0, 0.0});
	p = translate(p, v);
	p = rotate(p, deg);
	p = translate(p, scaleBy(v, -1.0));
	return p;
}

double dist (point u, point v) { return hypot(u.x - v.x, u.y - v.y); }
/*===================================================================*/
point sectionLS (point u, point v, double r) { return translate(u, scaleBy(vec(u, v), r)); }
point midPoint (point u, point v) { return point((u.x + v.x) / 2, (u.y + v.y) / 2); }

point closestPointToLS (point p1, point p2, point x) {
	vec u (p1, x);
	vec v (p1, p2);
	double s = projScaleFactor(u, v);
	dbg(s);
	if (s < 0.0) return p1;
	if (s > 1.0) return p2;
	return translate(p1, scaleBy(v, s));
}

double triangleArea (double a, double b, double c) {
	double s = (a + b + c) / 2;
	return sqrt(s * (s - a)) * sqrt((s - b) * (s - c));
}

double triangleArea (point p1, point p2, point p3) { return triangleArea(dist(p1, p2), dist(p2, p3), dist(p3, p1)); }
double incenterRadius (double a, double b, double c) { return 2 * triangleArea(a, b, c) / (a + b + c); }
double incenterRadius (point p1, point p2, point p3) { return incenterRadius(dist(p1, p2), dist(p2, p3), dist(p3, p1)); }
double circumcircleRadius (double a, double b, double c) { return (a * b * c) / (4 * triangleArea(a, b, c)); }
double circumcircleRadius (point p1, point p2, point p3) { return circumcircleRadius(dist(p1, p2), dist(p2, p3), dist(p3, p1)); }

point circumcircleCenter (point p1, point p2, point p3) {
	point m1 = midPoint(p1, p2);
	vec v1 = rotate(vec(p1, p2), 90.0);
	line l1 = line(m1, translate(m1, v1));

	point m2 = midPoint(p2, p3);
	vec v2 = rotate(vec(p2, p3), 90.0);
	line l2 = line(m2, translate(m2, v2));

	point c;
	areIntersect(l1, l2, c);
	return c;
}

bool circleCenter (point p1, point p2, double r, point& c) {
	double d = dist(p1, p2) / 2;
	double l = r * r - d * d;
	if (l < 0.0) return false;
	l = sqrt(l);
	vec v = rotate(vec(p1, p2), 90.0);
	v = scaleTo(v, l);
	c = translate(midPoint(p1, p2), v);
	return true;
}
/*===================================================================*/