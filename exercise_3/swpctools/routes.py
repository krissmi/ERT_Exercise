
import os
import json
import logging
import pwd
import grp
import psutil

from flask import Blueprint, current_app, render_template

swpc_bp = Blueprint('swpc', __name__, url_prefix='/', template_folder='templates')


def register_routes():
    logger = logging.getLogger(__name__)
    logger.info('registering endpoint template: {}'.format(swpc_bp.name))
    current_app.register_blueprint(swpc_bp)


@swpc_bp.route("/")
def swpc_root():
    template_name = '_swpc_root.html'

    logger = logging.getLogger(__name__)

    logger.info('rendering template: {}'.format(template_name))
    return render_template(template_name)


@swpc_bp.route("/config")
def swpc_config():
    logger = logging.getLogger(__name__)
    template_name = 'config_and_status.html'

    args = current_app.config['args']

    user = pwd.getpwuid(os.getuid())
    group = os.getgrouplist(user.pw_name, user.pw_gid)[0]
    group = grp.getgrgid(group)
    group = group.gr_name
    user = user.pw_name

    cpu_times = psutil.cpu_times()
    memory = psutil.virtual_memory()

    status = {
        'pid': os.getpid(),
        'user': '{}:{}'.format(user, group),
        'workpath': os.getcwd(),
        'datapath': args.datapath,
        'logspath': args.logspath,
        'verbose': args.verbose,
        'cpu': ', '.join("[{}={}]".format(key,str(value)) for key, value in cpu_times._asdict().items()),
        'memory (%)': memory.percent,
        'memory (a)': memory.available,
        'memory (u)': memory.used,
        'memory (f)': memory.free,
    }
    status_json = json.dumps(status, indent=4)
    logger.debug('status json: {}'.format(status_json))

    return render_template(template_name, status=status)


@swpc_bp.route("/about")
def swpc_about():
    template_name = 'about.html'

    logger = logging.getLogger(__name__)

    logger.info('rendering template: {}'.format(template_name))
    return render_template(template_name)

# END-OF-FILE
