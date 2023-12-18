
import argparse
import logging

from . import request, datastore


def pull(args: argparse.Namespace) -> list:
    logger = logging.getLogger()  # root logger
    logger.info("pulling records from endpoint: {}".format(args.endpoint))

    req = request.RtswRequest()
    dataset = req.records()
    logger.debug('dataset: %s', dataset)

    ds = datastore.RtswDataStore(datafile=args.datafile)
    dataframe = ds.frame_from(dataset=dataset)
    ds.info(frame=dataframe)
    ds.write(frame=dataframe)

    return dataset


def dump(args: argparse.Namespace) -> str or None:
    logger = logging.getLogger()  # root logger
    logger.info("pulling records from datafile: {}".format(args.datafile))

    try:
        ds = datastore.RtswDataStore(datafile=args.datafile)
        dataframe = ds.read()
        dataset = '-'
        dataset += ds.to_csv(frame=dataframe)
        ds.info(frame=dataframe)
        return dataset
    except FileNotFoundError:
        logger.error('dataframe file not found: {}'.format(args.datafile))
        return None

# END-OF-FILE
