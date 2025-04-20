from flask import Blueprint, jsonify, request 
# Blueprint: создание префикса для конечной точки
# jsonify: преобразование данных в JSON
# request: доступ к данным запроса
from app.models import db, User, Deadline
# db: объект базы данных
# User: модель пользователя
# Deadline: модель дедлайна
from app.utils.jwtdec import token_required
# token_required: декоратор ограничивающий конечную точку только для авторизированных пользователей

deadlines_bp = Blueprint('/api/deadlines', __name__)

@deadlines_bp.route('/getdeadlines', methods=['GET'])
@token_required
def getDeadlines(user):
    deadlines = Deadline.query.filter_by(user_id=user.id)
    return jsonify({"deadlines": [{"id": task.id, "content": task.content, "endstamp": task.endstamp} for task in deadlines]}), 200

@deadlines_bp.route('/adddeadline', methods=["POST"])
@token_required
def addDeadline(user):
    content = request.args.get("content")
    if content is None:
        return jsonify({"error": "Content is required"}), 400
    
    endstamp = request.args.get("endstamp")
    if endstamp is None:
        return jsonify({"error": "Timestamp is required"}), 400
    
    deadline = Deadline(user_id=user.id, content=content, endstamp=endstamp)
    db.session.add(deadline)
    db.session.commit()

    return jsonify({"message": "Deadline added"}), 200

@deadlines_bp.route('/deletedeadline/<int:deadlineId>', methods=["DELETE"])
@token_required
def deleteDeadline(user, deadlineId):
    deadline = Deadline.query.get(deadlineId)
    if deadline is None:
        return jsonify({"error": "Task not found"}), 404
    
    db.session.delete(deadline)
    db.session.commit()

    return jsonify({"message": "Deadline deleted"}), 200