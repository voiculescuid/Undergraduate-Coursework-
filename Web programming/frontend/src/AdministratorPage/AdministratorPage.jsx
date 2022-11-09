import React from 'react';
import { connect } from 'react-redux';

import { fileActions } from '../_actions';

import './AdministratorPage.module'

class AdministratorPage extends React.Component {
    componentDidMount() {
        this.props.getUsers();
    }

    handleDeleteUser(id) {
        return (e) => this.props.deleteUser(id);
    }

    render() {
        const { user, files } = this.props;
        return (
            <div className="col-lg">
                <h3>All registered file:</h3>
                {files.loading && <em>Loading files...</em>}
                {files.error && <span className="text-danger">ERROR: {files.error}</span>}
                {files.items &&
                    <ul>
                        {files.items.map((file, index) =>
                            <li key={file._id}>
                                {file.fileName + ' ' + file.fileHash}
                                {
                                    file.deleting ? <em> - Deleting...</em>
                                    : file.deleteError ? <span className="text-danger"> - ERROR: {file.deleteError}</span>
                                    : <span> - <a onClick={this.handleDeleteUser(file._id)}>Delete</a></span>
                                }
                            </li>
                        )}
                    </ul>
                }
            </div>
        );
    }
}

function mapState(state) {
    const { files, authentication } = state;
    const { user } = authentication;
    return { user, files };
}

const actionCreators = {
    getUsers: fileActions.getAll,
    deleteUser: fileActions.delete
}

const connectedHomePage = connect(mapState, actionCreators)(AdministratorPage);
export { connectedHomePage as AdministratorPage };