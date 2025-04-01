from .config import db # импортируем базу данных из config.py

# этот класс нужен для создания таблицы в базе по его свойствам
# т.е. такие же столбцы будут созданы в базе, на основе находящихся классов в этом файле
class User(db.Model): 
    id = db.Column(db.Integer, primary_key=True) # id пользователя
    username = db.Column(db.String(80), unique=True, nullable=False) # имя пользователя
    hash = db.Column(db.String(120), nullable=False) # захэшированный пароль
    role = db.Column(db.String(120), nullable=False) # роль пользователя(права доступа)