from datetime import datetime

from cs50 import SQL
from flask import Flask, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get('name')
        month = request.form.get('month')
        day = request.form.get('day')
        try:
            datetime(2022, int(month), int(day))  # month/day validation
            if name:
                db.execute("insert into birthdays (name, month, day) values(?, ?, ?)", name, month, day);
        except Exception:
            pass
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        items = db.execute("select * from birthdays")

        return render_template("index.html", items=items)
