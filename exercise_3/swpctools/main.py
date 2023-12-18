
import os
import argparse
import logging
import logging.config
from pathlib import Path
import json

from . import exceptions, service
from .endpoints.rtsw import main as rtsw


def parse_command_line() -> argparse.Namespace:
    # common service options
    parser_common = argparse.ArgumentParser(add_help=False)
    parser_common.add_argument('--datapath', type=str, required=False,
                               default='data', metavar='PATH',
                               help='path to data files')
    parser_common.add_argument('--logspath', type=str, required=False,
                               default='logs', metavar='PATH',
                               help='path to logging files')

    # common service actions
    parser_actions = argparse.ArgumentParser(add_help=False)
    subparsers = parser_actions.add_subparsers(title="Commands", dest='command', required=True)
    subparsers.add_parser(name='pull', help='pull NOAA records and update the local data file')
    subparsers.add_parser(name='dump', help='dump NOAA records to a CSV file.')

    # module options
    parser = argparse.ArgumentParser(description='NOAA Space Weather Prediction Center Tool')
    parser.add_argument('-v', '--verbose',
                        action='store_true',
                        help="verbose output and logging")

    # TODO: this is problematic and high maintenance; dynamic loading?
    # endpoint commands (note: add new endpoints here)
    subparsers = parser.add_subparsers(title='NOAA Service Endpoints', dest='endpoint', required=True)

    parser_service = subparsers.add_parser('as-local-service', help='Local endpoint service',
                                         parents=[parser_common])
    parser_service.set_defaults(func=service.main, file='data/rtsw.parquet')

    parser_rtsw = subparsers.add_parser('rtsw', help='Real-Time Solar Wind',
                                        parents=[parser_common, parser_actions])
    parser_rtsw.set_defaults(func=rtsw.main, file='data/rtsw.parquet')

    # parse command-line
    return parser.parse_args()


def main() -> int:
    # parse command-line options
    args = parse_command_line()

    # get the root package namd and path
    package_name = Path(__package__)
    package_path = Path(os.path.dirname(__file__))

    # setup package logging
    logsfile = package_name.with_suffix('.log')
    logsfile = os.path.join(args.logspath, logsfile.name)

    os.makedirs(args.logspath, exist_ok=True)

    config_path = os.path.join(package_path, 'logging.json')
    with open(config_path) as logging_file:
        logging_string = logging_file.read()
    logging_config = json.loads(logging_string)
    logging_config['handlers']['file_handler']['filename'] = logsfile
    logging.config.dictConfig(logging_config)

    logger = logging.getLogger()  # root logger
    if args.verbose:
        logger.setLevel(logging.DEBUG)
    else:
        logger.setLevel(logging.INFO)

    logger.info('using log file: {}'.format(logsfile))

    # check service endpoint string
    if not isinstance(args.endpoint, str):
        raise exceptions.SwpcUnknownEndpointError('Unknown service endpoint name')
    logger.info('detected endpoint service: %s', args.endpoint)

    # configure datafile path
    match args.endpoint:
        case 'as-local-service':
            endpoint_name = 'swpc'
        case _:
            endpoint_name = args.endpoint

    os.makedirs(args.datapath, exist_ok=True)
    args.datafile = os.path.join(args.datapath, '{}.parquet'.format(endpoint_name))
    logger.info('using data file path: {}'.format(args.datafile))

    return args.func(args)

# END-OF-FILE
