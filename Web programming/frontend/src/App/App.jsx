import React from 'react';
import { Router, Route, Switch, Redirect, Link } from 'react-router-dom';
import { connect } from 'react-redux';
import CookieConsent from "react-cookie-consent";

import { userService } from '../_services';
import { history, Role } from '../_helpers';
import { alertActions } from '../_actions';
import { PrivateRoute } from '../_components';

import { HomePage } from '../HomePage';
import { AdministratorPage } from '../AdministratorPage'
import { UserPage } from '../UserPage'
import { LoginPage } from '../LoginPage';
import { RegisterPage } from '../RegisterPage';
import { FAQPage } from '../FAQPage';

import './App.module';

class App extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            currentUser: null,
            isAdmin: false
        };
    }

    componentDidMount() {
        userService.currentUser.subscribe(x => this.setState({
            currentUser: x,
            isAdmin: x && x.role === Role.Admin
        }));
    }

    logout() {
        userService.logout();
        history.push('/login');
    }

    render() {
        const { currentUser, isAdmin } = this.state;
        const { alert } = this.props;
        return (
            <Router history={history}>
                {currentUser &&
                    <nav className="navbar navbar-expand navbar-dark bg-dark justify-content-center">
                        <div className="navbar-nav">
                            <Link to="/" className="nav-item nav-link">Home</Link>
                            {isAdmin && <Link to="/admin" className="nav-item nav-link">Admin</Link>}
                            {!isAdmin && <Link to="/user" className="nav-item nav-link">Dashboard</Link>}
                            <Link to="/faq" className="nav-item nav-link">FAQ</Link>
                            <Link to="/login" className="nav-item nav-link">Logout</Link>
                        </div>
                    </nav>
                }

                <div className="jumbotron">
                    <div className="container">
                        <div className=" d-flex justify-content-center">
                            {alert.message && <div className={`alert ${alert.type}`}>{alert.message}</div>}

                            <Switch>
                                <PrivateRoute exact path="/" component={HomePage} />
                                <PrivateRoute exact path="/admin" roles={[Role.Admin]} component={AdministratorPage} />
                                <PrivateRoute exact path="/user" roles={[Role.User]} component={UserPage} />
                                <PrivateRoute exact path="/faq" roles={[Role.Admin, Role.User]} component={FAQPage} />
                                <Route path="/login" component={LoginPage} />
                                <Route path="/register" component={RegisterPage} />
                                <Redirect from="*" to="/login" />
                            </Switch>

                        </div>
                    </div>
                </div>

                <CookieConsent
                    enableDeclineButton
                    flipButtons
                    location="bottom"
                    cookieName="cookie"
                    expires={150}
                    debug={true} >
                    This website stores cookies on your computer. 
                    These cookies are used to collect information about how you interact with our 
                    website and allow us to remember you. We use this information in order to improve and 
                    customize your browsing experience and for analytics and metrics about our visitors both on 
                    this website and other media. To find out more about the cookies we use, see our Privacy Policy.{" "}
                </CookieConsent>
            </Router>
        );
    }
}

function mapState(state) {
    const { alert } = state;
    return { alert };
}

const actionCreators = {
    clearAlerts: alertActions.clear
};

const connectedApp = connect(mapState, actionCreators)(App);
export { connectedApp as App };