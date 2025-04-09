from flask import Blueprint, jsonify, request 
# Blueprint: создание префикса для конечной точки
# jsonify: преобразование данных в JSON
# request: доступ к данным запроса
from app.models import Auephase

currentId = 1

aue_bp = Blueprint('/api/aue', __name__)

@aue_bp.route('/getphase', methods=['GET'])
def getphase():
    global currentId
    phase = Auephase.query.get(currentId)
    if phase:
        currentId += 1
        return jsonify({'phase': phase.phase})
    else:
        currentId = 1
        phase = Auephase.query.get(currentId)
        return jsonify({'phase': phase.phase})