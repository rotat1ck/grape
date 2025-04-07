from flask import Blueprint, jsonify, request 
# Blueprint: создание префикса для конечной точки
# jsonify: преобразование данных в JSON
# request: доступ к данным запроса
from app.models import db, Note
# db: объект базы данных
# User: модель пользователя
from app.utils.jwtdec import token_required, create_token
# token_required: декоратор ограничивающий конечную точку только для авторизированных пользователей
# create_token: функция генерации токена

notes_bp = Blueprint('/api/notes', __name__)

@notes_bp.route('/addnote', methods=['POST'])
@token_required # декоратор который не пропустит запрос без валидного токена, возвращает в функцию юзера
def addNote(user):
    note = request.form.get('note') # получение заметки
    start = request.form.get('startstamp') # получение временной unix точки старта
    end = request.form.get('endstamp') # получение временной unix точки конца

