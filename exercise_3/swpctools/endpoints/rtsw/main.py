
import sys
import argparse
import logging

from . import commands


def main(args: argparse.Namespace) -> int:
    logger = logging.getLogger()  # root logger

    # TODO: this is problematic and high maintenance; dynamic loading?
    logger.info('matching command: {}'.format(args.command))
    match args.command:
        case 'pull':
            commands.pull(args=args)

        case 'dump':
            dataset = commands.dump(args=args)
            print(dataset, file=sys.stdout)  # print to stdout

    return 0

# END-OF-FILE
