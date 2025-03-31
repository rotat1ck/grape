from app import startApp # <= функция которая создает приложение и подключает все конечные точки
from app.config import db

app = startApp() # <= вызов данной фунции

with app.app_context():
    db.create_all() # <= создание таблиц в базе данных

if __name__ == '__main__':
    app.run() # <= запуск сервера
