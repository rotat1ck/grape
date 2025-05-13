from flask import Flask
from .config import initConfig # <= файл конфигурации, создает базу данных и вытаскивает параметры среды
# параметры среды определяются в файле .env, его нет на гитхабе в целях безопастности сервера
from .routes.users import users_bp # <= подключение путей, переменные заканчивающиеся на _bp определяют 
# какой будет префикс для конечной точки, пример: grape.rotatick.ru/api/users/login, где /api/users префикс 
# для конечной точки login
from .routes.aue import aue_bp
from .routes.tasks import tasks_bp
from .routes.deadlines import deadlines_bp
from .routes import default_bp


def startApp():
    app = Flask(__name__) # создание переменной приложения
    initConfig(app) # запуск файла конфигурации config.py

    app.register_blueprint(default_bp, url_prexif='/')
    app.register_blueprint(users_bp, url_prefix='/api/users') # <= обозначение префикса /api/users
    app.register_blueprint(aue_bp, url_prefix='/api/aue')
    app.register_blueprint(tasks_bp, url_prefix='/api/tasks')
    app.register_blueprint(deadlines_bp, url_prefix='/api/deadlines')

    return app # возвращаем объект приложения в main.py для запуска