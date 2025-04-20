from flask import Blueprint, jsonify, request 
# Blueprint: создание префикса для конечной точки
# jsonify: преобразование данных в JSON
# request: доступ к данным запроса
from app.models import db, User, Task
# db: объект базы данных
# User: модель пользователя
# Task: модель задачи
from app.utils.jwtdec import token_required
# token_required: декоратор ограничивающий конечную точку только для авторизированных пользователей

tasks_bp = Blueprint('/api/tasks', __name__)

@tasks_bp.route('/gettasks', methods=['GET'])
@token_required
def getTasks(user):
    tasks = Task.query.filter_by(user_id=user.id)
    return jsonify({"tasks": [{"id": task.id, "content": task.content} for task in tasks]}), 200

@tasks_bp.route('/addtask', methods=["POST"])
@token_required
def addTask(user):
    content = request.args.get("content")
    if content is None:
        return jsonify({"error": "Content is required"}), 400
    
    task = Task(user_id=user.id, content=content)
    db.session.add(task)
    db.session.commit()

    return jsonify({"message": "Task added"}), 200

@tasks_bp.route('/deletetask/<int:taskId>', methods=["DELETE"])
@token_required
def deleteTask(user, taskId):
    task = Task.query.get(taskId)
    if task is None:
        return jsonify({"error": "Task not found"}), 404
    
    db.session.delete(task)
    db.session.commit()

    return jsonify({"message": "Task deleted"}), 200