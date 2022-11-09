from flask import Flask, render_template, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy
from flask_login import UserMixin, LoginManager, current_user, login_user, logout_user

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://docker:docker@localhost:32768/mps_project_1'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SECRET_KEY'] = "j03j9f870923j0485f723405f"
db = SQLAlchemy(app)
login_manager = LoginManager(app)


@login_manager.user_loader
def load_user(user_id):
    return Users.query.get(int(user_id))


class Users(db.Model, UserMixin):
    user_id = db.Column(db.Integer, primary_key=True)
    user_name = db.Column(db.String(255))
    user_password = db.Column(db.String(255))
    user_authority = db.Column(db.String(255))
    user_keyword = db.Column(db.String(255))

    def get_id(self):
        return self.user_id


class Competitors(db.Model):
    competitor_id = db.Column(db.Integer, primary_key=True)
    competitor_name = db.Column(db.String(255))
    competitor_numb = db.Column(db.Integer)
    competitor_grade = db.Column(db.Integer)


class Comp(db.Model):
    comp_id = db.Column(db.Integer, primary_key=True)
    comp_name = db.Column(db.String(255))
    comp_description = db.Column(db.String(255))
    comp_type = db.Column(db.String(255))
    comp_rounds = db.Column(db.Integer)
    comp_keyword = db.Column(db.String(255))
    comp_start_timestamp = db.Column(db.Time)
    comp_stop_timestamp = db.Column(db.Time)
    comp_status = db.Column(db.String(255))


class Rounds(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    round_comp_id = db.Column(db.Integer)
    round_id = db.Column(db.Integer)
    round_description = db.Column(db.String(255))
    round_start_timestamp = db.Column(db.Time)
    round_stop_timestamp = db.Column(db.Time)
    round_status = db.Column(db.String(255))


class Comments(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    comment_id = db.Column(db.Integer)
    comment_author = db.Column(db.Integer)
    comment_timestamp = db.Column(db.Time)
    comment_content = db.Column(db.String(255))


class Roundcompetitors(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    round_comp_id = db.Column(db.Integer)
    round_competitor_name = db.Column(db.String(255))
    round_competitor_numb = db.Column(db.Integer)


@app.route("/error", methods=["GET", "POST"])
def error():
    errorCode = request.args.get('error')
    return render_template("error.html", error=errorCode)


@app.route("/showcompetitors", methods=["GET", "POST"])
def showcompetitors():
    if not current_user.is_authenticated:
        return render_template("error.html", error=1)
    competitors = Competitors.query.all()
    return render_template("showparticipants.html", paritcipants=competitors)


@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        login = Users.query.filter_by(user_name=username, user_password=password).first()
        if login is not None:
            login_user(login)
            return redirect(url_for("index"))
    return render_template("error.html", error=3)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        name = request.form["username"]
        password = request.form["password"]
        keyword = request.form["keyword"]
        db.session.add(Users(user_name=name, user_password=password, user_authority='jury', user_keyword=keyword))
        db.session.commit()
        return render_template("error.html", error=4)
    return redirect(url_for("home"))


@app.route("/logout")
def logout():
    logout_user()
    return redirect(url_for('home'))


@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == "POST":
        return render_template('home.html')
    return render_template('home.html')


@app.route('/home', methods=['GET', 'POST'])
def home():
    return render_template('home.html')


@app.route('/createevent', methods=['GET', 'POST'])
def createevent():
    if not current_user.is_authenticated:
        return render_template("error.html", error=1)
    return render_template('createevent.html')


@app.route('/showevent', methods=['GET', 'POST'])
def showevent():
    if not current_user.is_authenticated:
        return render_template("error.html", error=1)
    comp = Comp.query.all()
    return render_template('showevent.html', competitions=comp)


@app.route('/jury', methods=['GET', 'POST'])
def jury():
    if not current_user.is_authenticated:
        return render_template("error.html", error=1)
    comp = Comp.query.filter(Comp.comp_status == 'finished').all()
    if len(comp) >= 1:
        jurythis = comp[0]

        participants = Roundcompetitors.query.filter(Roundcompetitors.round_comp_id == jurythis.comp_id).all()

        return render_template('jury.html', competition=jurythis, participants=participants)
    else:
        return render_template('jury.html')


@app.route('/showresult', methods=['GET', 'POST'])
def showresult():
    if not current_user.is_authenticated:
        return render_template("error.html", error=1)
    idreq = request.args.get('comp')
    competition = Comp.query.get(idreq)
    rounds = Rounds.query.filter(Rounds.round_comp_id == idreq).all()
    comments = Comments.query.all()
    return render_template('showresults.html', competition=competition, rounds=rounds, comments=comments)


@app.route('/display')
def display():
    competitors = Competitors.query.order_by(Competitors.competitor_grade.desc()).all()
    return render_template('display.html', paritcipants=competitors)


@app.route('/addcomment', methods=['GET', 'POST'])
def addcomment():
    if request.method == "POST":
        content = request.form["comment"]
        author = current_user.user_name
        timestamp = db.func.current_timestamp()
        compid = request.form["compid"]
        db.session.add(Comments(comment_author=author, comment_content=content, comment_timestamp=timestamp, comment_id=compid))
        db.session.commit()
        return redirect(url_for('showevent'))
    return render_template("error.html", error=5)


if __name__ == '__main__':
    app.run(debug=True)

