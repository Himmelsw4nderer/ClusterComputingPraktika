from flask import Flask, request, render_template, redirect, url_for, jsonify
from redis import Redis

app = Flask(__name__)
redis = Redis(host="redis", db=0, socket_timeout=5, charset="utf-8", decode_responses=True)

@app.route('/', methods=['GET'])
def index():
    students = redis.lrange('students', 0, -1)
    return render_template('index.html', students=students)

@app.route('/add_student', methods=['POST'])
def add_student():
    name = request.form['name']
    redis.rpush('students', {'name': name})
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)