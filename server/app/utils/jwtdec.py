from flask import current_app, request, jsonify
import jwt
from datetime import datetime, timedelta, timezone
from functools import wraps
from app.models import User

def create_token(username):
    current_time = datetime.now(timezone.utc)
    token = jwt.encode({
        'sub': username,
        'iat': current_time,
        'exp': current_time + timedelta(minutes=30)
    }, current_app.config['SECRET_KEY'], algorithm='HS256')
    return token

def token_required(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        token = None
        if 'Authorization' in request.headers:
            token = request.headers['Authorization'].split()[1]

        if not token:
            return jsonify({'error': 'Token is missing'}), 401

        try:
            data = jwt.decode(token, current_app.config['SECRET_KEY'], algorithms=['HS256'])
            current_user = data['sub']
            user = User.query.filter_by(username=current_user).first()
            
            if user.banned:
                return jsonify({'error': 'User is banned'}), 403
            
        except jwt.ExpiredSignatureError:
            return jsonify({'error': 'Expired token'}), 401
        except jwt.InvalidTokenError:
            return jsonify({'error': 'Invalid token'}), 401

        return f(user, *args, **kwargs)

    return decorated