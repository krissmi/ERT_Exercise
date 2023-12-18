
import datetime
import os
import argparse
import logging

from flask import Flask
from waitress import serve

from . import routes as swpc_routes
from .endpoints import rtsw


def create_service(args: argparse.Namespace) -> Flask:
    logger = logging.getLogger() # root logger

    app = Flask(os.path.splitext(os.path.basename(__file__))[0])
    app.config['args'] = args

    if args.verbose:
        app.config['EXPLAIN_TEMPLATE_LOADING'] = True

    # app (template) context processors
    @app.context_processor
    def utility_processor():
        def now() -> datetime:
            return datetime.datetime.now(datetime.UTC)
        return dict(now=now)

    # register app routes (note: add endpoint routes here)
    with app.app_context():
        swpc_routes.register_routes()
        rtsw.routes.register_routes()

    return app


def main(args: argparse.Namespace) -> int:
    logger = logging.getLogger()  # root logger

    # create the app
    app = create_service(args=args)

    # start the gateway
    logger.info('starting server...')
    serve(app, host="0.0.0.0", port=8080)

    return 0

# END_OF_FILE
