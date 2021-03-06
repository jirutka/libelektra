/**
 * @file
 *
 * @brief connect the InstanceCard component to redux
 *
 * by mapping redux state and action creators to its properties
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'

import InstanceCard from '../components/InstanceCard.jsx'
import {
  updateInstance, deleteInstance,
} from '../actions'

const mapStateToProps = (state, { id }) => {
  return {}
}

const mapDispatchToProps = (dispatch) =>
  bindActionCreators({
    updateInstance, deleteInstance,
  }, dispatch)

export default connect(mapStateToProps, mapDispatchToProps)(InstanceCard)
