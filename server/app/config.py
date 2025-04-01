from flask_sqlalchemy import SQLAlchemy # <= библеотека для работы flask с sqlite
from os import getenv, path # <= библеотека для работы с файдами
from dotenv import load_dotenv # <= библеотека для работы с переменными среды (.env)

load_dotenv()  # <= загрузка переменных среды из файла .env
db = SQLAlchemy() # <= создание экземпляра класса SQLAlchemy, т.е объекта через который
# можно будет работать с базой данных

def initConfig(app):
    current_dir = path.dirname(path.abspath(__file__)) # нахождение текущего каталога, для создания базы
    db_path = path.join(current_dir, '..', 'grape.db') # определение пути базы
    # в данном случае мы выходим на уровень выше из текущего каталога и создаем базу рядом с main.py
    
    # параметры app.config это настройки приложения которые можно использовать из любой его точки
    # импортировав current_app из flask, т.е from flask import current_app
    app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{db_path}' # переменная пути базы данных
    app.config['SECRET_KEY'] = getenv("SECRET_KEY") # переменная для создания зашифрованных токенов
    db.init_app(app) # функция инициализации базы данных, она использует переменную приложения SQLALCHEMY_DATABASE_URI