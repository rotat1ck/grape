from flask import Blueprint, jsonify, request 
# Blueprint: создание префикса для конечной точки
# jsonify: преобразование данных в JSON
# request: доступ к данным запроса

users_bp = Blueprint("/api/users", __name__) # <= префикс для конечной точки
# /api/users/ и так записан в __init__.py но можно дублировать для улучшения читаемости

# user_bp.route это декоратор для выполнения функции
# он примает параметр конечной точки, в данном случае /login
# и http метод(ы) какие можно использовать совершая запрос
# в сумме получиться что функция usersLogin будет вызываться при запросе на
# grape.rotatick.ru/api/users/login с http методом GET
@users_bp.route("/login", methods=["GET"])
def usersLogin():
    return jsonify({"message": "Login page"}) # возвращаем Login page в виде JSON