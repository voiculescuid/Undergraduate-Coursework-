import { fileConstants } from '../_constants';

export function files(state = {}, action) {
  switch (action.type) {
    case fileConstants.GETALL_REQUEST:
      return {
        loading: true
      };
    case fileConstants.GETALL_SUCCESS:
      return {
        items: action.files
      };
    case fileConstants.GETALL_FAILURE:
      return { 
        error: action.error
      };
    case fileConstants.DELETE_REQUEST:
      return {
        ...state,
        items: state.items.map(file =>
          file._id === action.id
            ? { ...file, deleting: true }
            : file
        )
      };
    case fileConstants.DELETE_SUCCESS:
      return {
        items: state.items.filter(file => file._id !== action.id)
      };
    case fileConstants.DELETE_FAILURE:
      return {
        ...state,
        items: state.items.map(file => {
          if (file.id === action.id) {
            const { deleting, ...copy } = file;
            return { ...copy, deleteError: action.error };
          }

          return file;
        })
      };
    default:
      return state
  }
}