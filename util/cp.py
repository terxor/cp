import argparse, sys, subprocess, os, json

args = None

# Edit this dict to add/modify stuff
langs = {
  'Python': {
    'ext': ['py'],
    'run': lambda file, name, ext: f'python {file}'
  },
  'C++': {
    'ext': ['cpp', 'cc'],
    'run': lambda file, name, ext: f'{name}',
    'compile': lambda file, name, ext: f'g++ {file} -o {name} -std=c++17 -O2 -Wall -Wextra -DLOCAL'
  },
}

def run():
  lname = get_lang()
  cmd = langs[lname]['run'](*args.file)
  infile = None if args.infile is None else open(args.infile, 'r')
  outfile = None if args.outfile is None else open(args.outfile, 'wb')
  timeout = None if (args.time_limit is None or args.infile is None) else args.time_limit / 1000
  try:
    result = subprocess.run(cmd, cwd = os.getcwd(), timeout=timeout, stdin=infile, capture_output=True)
    if result.returncode != 0:
      raise Exception(f'Non-zero return code {result.returncode}')
  except Exception as err:
    print(f'Failed ({err})')
    return

  sep = '-' * 16
  if outfile is None:
    print('-- %s --' % ('out'))
    print(result.stdout.decode('utf-8'))
  else:
    outfile.write(result.stdout)
    outfile.flush()
    outfile.close()
  print('-- %s --' % ('err'))
  print(result.stderr.decode('utf-8'))

def compile():
  lname = get_lang()
  if 'compile' not in langs[lname]:
    print(f'No compile command for {lname}')
    return
  cmd = langs[lname]['compile'](*args.file)
  print(f'Compile {lname} [{cmd}]')
  result = subprocess.run(cmd, cwd = os.getcwd(), shell=True)
  print('Done' if result.returncode == 0 else 'Failed')

# Get lang object using given args file
def get_lang():
  file, n, ext = args.file
  for name, lang in langs.items():
    if ext in lang['ext']:
      return name
  raise Exception('Lang not found')

def action_type(s):
  if s not in ['compile', 'run']:
    raise TypeError()
  return s

def all_exts():
  exts = []
  for lang in langs.values():
    exts += lang['ext']
  return exts

def source_file(s):
  try:
    i = s.rindex('.')
    name, ext = s[:i], s[i+1:]
    if ext not in all_exts(): raise Exception()
    return [s, name, ext]
  except:
    raise TypeError()

def main():
  parser = argparse.ArgumentParser(description='Compile/run convenience utility')
  parser.add_argument('file', type=source_file, help='Source code file with extension. Extension can be one of: ' + ', '.join(all_exts()))
  parser.add_argument('action', type=action_type, help='compile or run')
  parser.add_argument('--infile', help='Input file. If not provided, standard input will be used. Only applicable for run')
  parser.add_argument('--outfile', help='Output file. If not provided, standard output will be used. Only applicable for run')
  parser.add_argument('--time_limit', type=int, help='Execution time limit in ms. Only applicable for run. Only applicable when input given through file.')
  global args
  args = parser.parse_args()

  if args.action == 'run':
    run()
  else:
    compile()

if __name__ == '__main__':
  main()