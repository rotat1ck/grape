from flask import current_app, request, jsonify # стандартные библиотеки, подробнее в app/routes/users.py и app/config.py
import jwt # библиотека для создания токена
from datetime import datetime, timedelta, timezone # библеотеки для проверки токена на истечение
from functools import wraps # библиотека для создания кастомных декораторов
from app.models import User # модель пользователя из models.py, через модели базы данных очень просто с ней взаимодействовать

def create_token(username): # <= функция создания токена
    current_time = datetime.now(timezone.utc)
    token = jwt.encode({
        'sub': username, # добавляем в токен имя пользователя
        'iat': current_time, # добавляем в токен время создания токена
        'exp': current_time + timedelta(minutes=30) # <= время жизни токена, 30 минут
    }, current_app.config['SECRET_KEY'], algorithm='HS256') # используем секретный ключ из .env для шифрования токена
    return token

def token_required(f): # <= кастомный декоратор
    @wraps(f)
    def decorated(*args, **kwargs): # <= функция, которая будет вызываться перед вызовом функции, которую мы декорируем
        token = None
        if 'Authorization' in request.headers: # <= если в запросе есть заголовок Authorization, т.е. если ли токен в запросе пользователя
            token = request.headers['Authorization'].split()[1]

        if not token: # <= если токена нет, возвращаем ошибку 401, не авторизован
            return jsonify({'error': 'Token is missing'}), 401

        try: # <= декодируем токен, используя секретный ключ из .env
            data = jwt.decode(token, current_app.config['SECRET_KEY'], algorithms=['HS256'])
            current_user = data['sub']
            user = User.query.filter_by(username=current_user).first() # <= ищем пользователя по имени, который мы получили из токена
            
        except jwt.ExpiredSignatureError:
            return jsonify({'error': 'Expired token'}), 401 # <= если токен просрочен, возвращаем ошибку 401, не авторизован
        except jwt.InvalidTokenError:
            return jsonify({'error': 'Invalid token'}), 401 # <= если токен невалиден, возвращаем ошибку 401, не авторизован

        return f(user, *args, **kwargs) # <= если все прошло успешно, вызываем функцию, которую мы декорируем и передаем в нее пользователя

    return decorated