
import logging
from flask import Blueprint, current_app, render_template

from . import commands

rtsw_bp = Blueprint('rtsw', __name__, url_prefix="/rtsw", template_folder='templates')


def register_routes():
    logger = logging.getLogger(__name__)
    logger.info('registering endpoint template: {}'.format(rtsw_bp.name))
    current_app.register_blueprint(rtsw_bp)


@rtsw_bp.route("/")
def rtsw_root():
    template_name = '_rtsw_root.html'

    logger = logging.getLogger(__name__)
    logger.debug('rendering template: {}'.format(template_name))
    return render_template(template_name)


@rtsw_bp.route("/pull")
def rtsw_pull():
    logger = logging.getLogger(__name__)
    template_name = "records_raw.html"
    args = current_app.config['args']

    dataset = commands.pull(args=args)

    logger.info('rendering template: {}'.format(template_name))
    return render_template(template_name, dataset=dataset)


@rtsw_bp.route("/dump")
def rtsw_dump():
    logger = logging.getLogger(__name__)
    template_name = "records_csv.html"
    args = current_app.config['args']

    dataset = commands.dump(args=args)

    logger.info('rendering template: {}'.format(template_name))
    return render_template(template_name, dataset=dataset)

# END-OF-FILE
