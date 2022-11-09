import { fileConstants } from '../_constants';
import { fileService } from '../_services';

export const fileActions = {
    getAll,
    delete: _delete
};

function getAll() {
    return dispatch => {
        dispatch(request());

        fileService.getAll()
            .then(
                files => dispatch(success(files)),
                error => dispatch(failure(error.toString()))
            );
    };

    function request() { return { type: fileConstants.GETALL_REQUEST } }
    function success(files) { return { type: fileConstants.GETALL_SUCCESS, files } }
    function failure(error) { return { type: fileConstants.GETALL_FAILURE, error } }
}

function _delete(id) {
    return dispatch => {
        dispatch(request(id));

        fileService.delete(id)
            .then(
                file => dispatch(success(id)),
                error => dispatch(failure(id, error.toString()))
            );
    };

    function request(id) { return { type: fileConstants.DELETE_REQUEST, id } }
    function success(id) { return { type: fileConstants.DELETE_SUCCESS, id } }
    function failure(id, error) { return { type: fileConstants.DELETE_FAILURE, id, error } }
}