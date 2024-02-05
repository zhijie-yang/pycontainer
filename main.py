import argparse
import sys
import os
import build.pycontainer as pycontainer


def parse_args(argv: list[str]):
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--volume', action='append', 
                        help='Volume mapping, /source/path:/target/path')
    parser.add_argument('-n', '--name', required=True, type=str,
                        help='Name of the container')
    parser.add_argument('command', nargs=argparse.REMAINDER,
                        help='The command to run')
    return parser.parse_args()


def main(argv: list[str] = sys.argv):
    if os.geteuid():
        print("This code must run with root privilege!")
        exit(1)
    args = parse_args(argv)

    if args.volume:
        mapped_paths = [tuple(kv.split(':')) for kv in args.volume]
        for kv in mapped_paths:
            assert len(kv) == 2
    else:
        mapped_paths = []

    task = pycontainer.Task(args.name, mapped_paths)
    task.start(args.command)

if __name__ == '__main__':
    main()
