from .config import db # импортируем базу данных из config.py

# этот класс нужен для создания таблицы в базе по его свойствам
# т.е. такие же столбцы будут созданы в базе, на основе находящихся классов в этом файле
class User(db.Model):
    __tablename__ = 'users' # название таблицы
    id = db.Column(db.Integer, primary_key=True) # id пользователя
    username = db.Column(db.String(80), unique=True, nullable=False) # имя пользователя
    email = db.Column(db.String(120), unique=True, nullable=False) # email пользователя
    hash = db.Column(db.String(120), nullable=False) # захэшированный пароль

class Note(db.model):
    __tablename__ = 'notes' # название табилцы
    id = db.Column(db.Integer, primary_key=True) # id заметки
    user_id = db.Column(db.Integer, db.ForeignKey('user.id')) # id пользователя
    note = db.Column(db.String(1024), nullable=False) # id пользователя