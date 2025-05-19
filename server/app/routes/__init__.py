from flask import Blueprint, current_app, jsonify, send_file, render_template, url_for
import os

default_bp = Blueprint('/', __name__)

@default_bp.route('/', methods=['GET'])
def indexPage():
    background_image_url = url_for('static', filename='img/back_site.jpeg')
    return render_template('index.html', background_image_url=background_image_url)

@default_bp.route('/download', methods=['GET'])
def downloadFile():
    path = os.path.join(current_app.config['INSTALLER_PATH'], "GrapeSetup-1.0.0.exe")
    
    if not os.path.isfile(path):
        return jsonify({"error": "File not found"}), 404

    return send_file(path, as_attachment=True)