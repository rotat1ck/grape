from .config import db

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    hash = db.Column(db.String(120), nullable=False)
    role = db.Column(db.Integer, nullable=False)
    banned = db.Column(db.Boolean, nullable=False, default=False)
    cooldown = db.Column(db.Integer, nullable=False, default=0)