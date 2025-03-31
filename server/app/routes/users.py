from flask import Blueprint, jsonify, request

users_bp = Blueprint("/users", __name__)

@users_bp.route("/login", methods=["GET"])
def usersLogin():
    return jsonify({"message": "Login page"})