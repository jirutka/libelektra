/**
 * @file
 *
 * @brief handle actions related to operations on the *shallow*
 * Elektra key database (kdb), which only contains paths
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

import {
  GET_KDB_SUCCESS, DELETE_KEY_SUCCESS, SET_KEY_SUCCESS, MOVE_KEY_SUCCESS,
} from '../actions'

// controls the state of the paths available in the kdb
export default function pathReducer (state = [], action) {
  switch (action.type) {
    case GET_KDB_SUCCESS: {
      if (action.result && action.result.ls) {
        return action.result.ls
      }
      return state
    }

    case DELETE_KEY_SUCCESS: {
      const { path } = action && action.request
      return state.filter(p => (p !== path) && !p.startsWith(path + '/'))
    }

    case SET_KEY_SUCCESS: {
      const { path } = action && action.request
      return state.includes(path)
        ? state
        : [ ...state, path ]
    }

    case MOVE_KEY_SUCCESS: {
      const { from, to } = action && action.request
      const newState = state.filter(p => (p !== from) && !p.startsWith(from + '/'))
      const newChildren = state.filter(p => p.startsWith(from + '/'))
        .map(p => {
          const name = p.split('/').pop()
          return to + '/' + name
        })
      return [ ...newState, to, ...newChildren ]
    }

    default:
      return state
  }
}
