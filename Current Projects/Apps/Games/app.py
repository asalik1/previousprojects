from flask import Flask, render_template, request, redirect, url_for
from helpers import public_routes, file_content

app = Flask(__name__, template_folder="./templates", static_folder='static')
    
@app.route('/')
def index():
    return "Running Flask App..."

@app.route('/about')
def about():
    content = file_content('./txt/About_content.txt')
    return render_template('about.html', title='About', content=content)

@app.route('/welcome')
def welcome():
    links = [(url_for(route), description) for route, description in public_routes]
    return render_template('welcome.html', links=links, title='Welcome')

@app.route('/game1')
def game_1():
    return render_template('game1.html', title='Game 1')

@app.route('/game2')
def game_2():
    return render_template('game2.html', title='Game 2')

if __name__ == '__main__':
    app.run('127.0.0.1', 5000, debug=True)
