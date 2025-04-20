from flask import Blueprint, jsonify, request 
# Blueprint: создание префикса для конечной точки
# jsonify: преобразование данных в JSON
# request: доступ к данным запроса
from app.models import db, User
# db: объект базы данных
# User: модель пользователя
from app.utils.jwtdec import token_required, create_token
# token_required: декоратор ограничивающий конечную точку только для авторизированных пользователей
# create_token: функция генерации токена


users_bp = Blueprint("/api/users", __name__) # <= префикс для конечной точки
# /api/users/ и так записан в __init__.py но можно дублировать для улучшения читаемости

# user_bp.route это декоратор для выполнения функции
# он примает параметр конечной точки, в данном случае /login
# и http метод(ы) какие можно использовать совершая запрос
# в сумме получиться что функция usersLogin будет вызываться при запросе на
# grape.rotatick.ru/api/users/login с http методом POST

@users_bp.route("/login", methods=["POST"])
def usersLogin():
    username = request.args.get('username')
    password = request.args.get('password')
    if not username: # проверка наличия имени пользователя в запросе
        return jsonify({"error": "Email or username is required"}), 400
    
    if not password: # проверка наличия пароля в запросе
        return jsonify({"error": "Password is required"}), 400
    
    user = User.query.filter_by(username = username).first() # ищем по имени пользователя
    if not user: # проверка пользователя по имени
        user = User.query.filter_by(email = username).first() # ищем по email
        if not user: # проверка пользователя по почте
            return jsonify({"error": "Invalid username or password"}), 401
    
    if user.hash != password: # проверка пароля
        return jsonify({"error": "Invalid username or password"}), 401
    
    # пользователь найден и пароль совпал
    return jsonify({"token": create_token(user.username)}), 200 # возвращаем токен пользователю

@users_bp.route('/register', methods=['POST'])
def usersRegister():
    email = request.args.get('email')
    username = request.args.get('username')
    password = request.args.get('password')

    if not email: # проверка наличия email в запросе
        return jsonify({"error": "Email is required"}), 400
    if not username: # проверка наличия имени пользователя в запросе
        return jsonify({"error": "Username is required"}), 400
    if not password: # проверка наличия пароля в запросе
        return jsonify({"error": "Password is required"}), 400
    
    user = User.query.filter_by(username = username).first() # ищем по имени пользователя
    if user: # проверка пользователя по имени
        return jsonify({"error": "Account with this username already exists"}), 400
    
    user = User.query.filter_by(email = email).first() # ищем по email
    if user: # проверка пользователя по email
        return jsonify({"error": "Account with this email already exists"}), 400
    
    new = User(username = username, email = email, hash = password) # создаем нового пользователя
    db.session.add(new) # добавляем пользователя в базу данных
    db.session.commit() # сохраняем изменения в базе данных

    return jsonify({"token": create_token(username)}), 200 # возвращаем токен пользователю