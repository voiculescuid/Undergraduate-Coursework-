import React from 'react';

import Button from 'react-bootstrap/Button';

import './UserPage.module'

class UserPage extends React.Component {
    render() {
        const { user, users } = this.props;
        return (
            <div className="col-md-9 col-md-offset-3">
                <Button variant="success">Download v1.0.0</Button><br/><br/>
                <Button variant="success">Download v1.0.1</Button><br/><br/>
                <Button variant="success">Download v1.0.2</Button><br/><br/>
            </div>
        );
    }
}

export { UserPage };