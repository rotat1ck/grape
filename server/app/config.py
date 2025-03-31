from flask_sqlalchemy import SQLAlchemy
from os import getenv, path
from dotenv import load_dotenv

load_dotenv() 
db = SQLAlchemy()

def initConfig(app):
    current_dir = path.dirname(path.abspath(__file__))
    db_path = path.join(current_dir, '..', 'grape.db')
    app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{db_path}'
    app.config['SECRET_KEY'] = getenv("SECRET_KEY")
    db.init_app(app)