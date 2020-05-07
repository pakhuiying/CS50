import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")
    #export API_KEY=pk_f36f8e0741f04582840901b4b894e5e3


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = int(session.get("user_id"))

    total_shares = db.execute("SELECT symbol, SUM(shares) as shares, SUM(price*shares) as cost FROM shares WHERE id = :user_id GROUP BY symbol",
    user_id=user_id)

    balance = db.execute("SELECT cash FROM users where id = :user_id",user_id = user_id)
    balance = round(balance[0]['cash'],2)

    for shares in total_shares: #total shares is a list of dictionaries
        symbol = shares["symbol"]
        stocks = lookup(symbol)
        name = stocks["name"]
        current_price = round(stocks["price"],2)
        shares['name'] = name #add name field to dictionary
        shares['current_share'] = current_price #add another field to dictionary
        shares['total_current_share'] = round(current_price * shares["shares"],2) #add another field to dictionary

    total_current_share = sum(shares['total_current_share'] for shares in total_shares)
    total_current_share = round(total_current_share,2)
    total_assets = round(balance + total_current_share,2)

    return render_template("index.html", shares = total_shares, balance = balance, total_assets = total_assets)




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    user_id = int(session.get("user_id"))
    symbol_net_share = db.execute("SELECT DISTINCT symbol, SUM(shares) as netshare FROM shares WHERE id = :user_id GROUP BY symbol", user_id = user_id)


    if request.method == "GET":
        return render_template("buy.html", symbol_net_share = symbol_net_share)

    else:
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol", 403)
        elif lookup(request.form.get("symbol")) == None:
            return apology("stock does not exist", 403)
        elif not request.form.get("shares"):
            return apology("must provide stock's share", 403)
        elif int(request.form.get("shares")) <= 0:
            return apology("must provide positive integer", 403)

        #if all clear, lookup stocks
        stocks = lookup(request.form.get("symbol"))
        #get stock price
        price_stock = stocks["price"]
        price_stock = round(int(price_stock), 2)
        symbol_stock = stocks["symbol"]
        name_stock = stocks["name"]
        #get no. of share
        share_stock = int(request.form.get("shares"))
        #get total stock price
        total_share_stock = share_stock * price_stock
        #check with user's balance


        balance = db.execute("SELECT (cash) FROM users WHERE id = :user_id",
                          user_id=user_id)
        balance = balance[0]["cash"]
        balance = round(balance - total_share_stock,2)

        #create table if it doesnt exist
        db.execute("CREATE TABLE IF NOT EXISTS shares (id INT, symbol VARCHAR(10), shares INT, price REAL, time TEXT)")

        if total_share_stock > balance:
            return apology("you don't have enough money", 403)
        else:
            db.execute("INSERT INTO shares (id, symbol, shares, price, time) VALUES (:user_id, :symbol, :shares, :price, :time)",
                user_id = user_id, symbol = symbol_stock, shares = share_stock, price = price_stock, time = datetime.datetime.now())
            db.execute("UPDATE users SET cash = :balance WHERE id = :user_id",
                balance = balance, user_id = user_id)
            return render_template("bought.html", symbol_stock = symbol_stock, name_stock = name_stock,
            share_stock = share_stock, price_stock = price_stock, total_share_stock = total_share_stock, balance = balance)







@app.route("/history")
@login_required
def history():

    """Show history of transactions"""
    user_id = int(session.get("user_id"))
    history = db.execute("SELECT * FROM shares WHERE id = :user_id", user_id = user_id)

    for hist in history:
        symbol = lookup(hist['symbol'])
        name = symbol['name']
        hist['name'] = name
        if hist['shares'] < 0:  #if shares is negative, assign a new field in dict as sold
            hist['action'] = "Sold"
            hist['shares'] = -1 * hist['shares']
        else: #if shares is positive, assign a new field in dict as bought
            hist['action'] = "Bought"

    return render_template("history.html", history = history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    # User reached route via GET, get lookup values
    if request.method == "GET":
        return render_template("quote.html")

    # User reached route via POST (as by submitting a form via POST)
    else:
        #symbol must be entered
        if not request.form.get("symbol"):
            return apology("must provide stock's symbol", 403)
        else:
            stocks = lookup(request.form.get("symbol"))
            name_stock = stocks["name"]
            price_stock = stocks["price"]
            symbol_stock = stocks["symbol"]
            return render_template("quoted.html",name_stock = name_stock, price_stock=price_stock, symbol_stock=symbol_stock)




@app.route("/register", methods=["GET", "POST"])
def register():
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted, implement one for if username matches database
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        #ensure confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 403)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Password do not match", 403)

        # Query database for username
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :pw)",
                          username=request.form.get("username"),
                          pw = generate_password_hash(request.form.get("password")))

        # Redirect user to home page
        return render_template("register_success.html")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = int(session.get("user_id"))
    time = datetime.datetime.now()

    symbol_net_share = db.execute("SELECT DISTINCT symbol, SUM(shares) as netshare FROM shares WHERE id = :user_id GROUP BY symbol", user_id = user_id)

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares")) #minus from shares table

        for item in symbol_net_share:
            if item['symbol'] == symbol:
                net_share = item['netshare']

        if not symbol:
            return apology("must choose stock", 403)
        elif not shares:
            return apology("must enter number of shares", 403)
        elif shares <= 0:
            return apology("must enter positive integer", 403)
        elif shares > net_share:
            return apology("must enter an integer < stocks you have", 403)


        shares_negative = 0 - shares
        current_share = lookup(symbol)
        name = current_share['name']
        current_share = round(current_share['price'],2)

        shares_cost = round(current_share * shares,2) #add to balance

        balance = db.execute("SELECT (cash) FROM users WHERE id = :user_id",
                          user_id=user_id)
        balance = balance[0]["cash"]
        balance = round(balance + shares_cost,2)

        #update cash balance
        db.execute("UPDATE users SET cash = :balance WHERE id = :user_id",
                balance = balance, user_id = user_id)

        #insert into shares
        db.execute("INSERT INTO shares (id, symbol, shares, price, time) VALUES (:user_id, :symbol, :shares_negative, :current_share, :time)",
                          user_id = user_id, symbol = symbol, shares_negative = shares_negative,
                          current_share = current_share, time = time)

        return render_template("sold.html", share_stock = shares, price_stock = current_share, total_share_stock = shares_cost,
        balance = balance, name = name, symbol = symbol)

    #if GET
    else:
        return render_template("sell.html", symbol_net_share = symbol_net_share)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
