import React from 'react';

import './HomePage.module'

class HomePage extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            currentUser: JSON.parse(localStorage.getItem('user')),
        };
    }

    render() {
        const { currentUser } = this.state;
        return (
            <div className="col-lg">

                <h1>Home</h1>
                <p>This site is for Donwload & Administration!</p>
                <p>Your role is: <strong>{currentUser.role}</strong>.</p>
                
            </div>
        );
    }
}

export { HomePage };