import os

from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from werkzeug.security import check_password_hash, generate_password_hash

from flask_session import Session
from helpers import apology, login_required, lookup, usd, get_cash, get_shares, validate_password

INITIAL_CASH = 10000

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    transaction_items = db.execute('select symbol, name, price, sum(shares) as shares from transactions '
                                   'where user_id = ? group by 1,2,3 order by 1,2,3', session["user_id"])
    transaction_items = [d | {'total_value': int(d.get('shares')) * (d.get('price'))} for d in transaction_items if
                         d.get('shares') > 0]
    cash = get_cash(db)
    return render_template('index.html', items=transaction_items, cash_available=cash, cash_total=INITIAL_CASH)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""  # allows a user to look up a stock’s current price.
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        quote = lookup(symbol)
        return render_template('quoted.html', item=quote)
    return render_template('quote.html')


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == 'POST':
        symbol = request.form.get('symbol')
        shares_number = int(request.form.get('shares'))
        quote = lookup(symbol)
        money_available = get_cash(db)

        new_cash = money_available - shares_number * quote.get('price')
        if new_cash >= 0:
            db.execute('update users set cash = ? where id = ?', new_cash, session['user_id'])
            db.execute('insert into transactions (user_id, symbol, name, shares, price) values(?,?,?,?,?)',
                       session['user_id'], symbol, quote.get('name'), shares_number, quote.get('price'))
            return redirect('/')
        else:
            return apology('no money')
    return render_template('buy.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        shares_number = int(request.form.get('shares'))
        quote = lookup(symbol)
        money_available = get_cash(db)
        shares_available = get_shares(db, symbol)

        new_cash = money_available + shares_number * quote.get('price')
        new_shares = shares_available - shares_number
        if new_shares >= 0:
            db.execute('update users set cash = ? where id = ?', new_cash, session['user_id'])
            db.execute('insert into transactions (user_id, symbol, name, shares, price) values(?,?,?,?,?)',
                       session['user_id'], symbol, quote.get('name'), -shares_number, quote.get('price'))
            return redirect('/')
        else:
            return apology('no shares')
    return render_template('sell.html')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transaction_items = db.execute('select * from transactions where user_id = ?', session["user_id"])
    return render_template('history.html', items=transaction_items)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    print('reg_1')
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation_pass = request.form.get('confirmation')

        if not username:  # TODO: check if already exists
            return apology("username is blank", 403)

        username_exist = db.execute('select username from users where username = ?', username)
        if username_exist:
            return apology("username already exists", 403)

        if not password:
            return apology("the password is blank", 403)

        if password != confirmation_pass:
            return apology("passwords do not match", 403)

        if not validate_password(password):
            return apology("password requires to consist of letters, numbers, and/or symbols.")

        db.execute('insert into users (username, hash, cash) values (?, ?, ?)', username,
                   generate_password_hash(password), INITIAL_CASH)

        return redirect('/')

    return render_template('register.html')

@app.route("/register2", methods=["GET", "POST"])
def register():
    """Register user"""
    print('reg_2')
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation_pass = request.form.get('confirmation')

        if not username:  # TODO: check if already exists
            return apology("username is blank", 403)

        username_exist = db.execute('select username from users where username = ?', username)
        if username_exist:
            return apology("username already exists", 403)

        if not password:
            return apology("the password is blank", 403)

        if password != confirmation_pass:
            return apology("passwords do not match", 403)

        if not validate_password(password):
            return apology("password requires to consist of letters, numbers, and/or symbols.")

        db.execute('insert into users (username, hash, cash) values (?, ?, ?)', username,
                   generate_password_hash(password), INITIAL_CASH)

        return redirect('/')

    return render_template('register.html')