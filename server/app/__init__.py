from flask import Flask
from .config import initConfig
from .routes.users import users_bp


def startApp():
    app = Flask(__name__)
    initConfig(app)

    app.register_blueprint(users_bp, url_prefix='/api/users')

    return app