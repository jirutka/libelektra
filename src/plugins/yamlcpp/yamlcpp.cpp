/**
 * @file
 *
 * @brief Source for yamlcpp plugin
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 *
 */

// -- Imports ------------------------------------------------------------------------------------------------------------------------------

#include "yamlcpp.hpp"
#include "yaml.h"

#include <kdb.hpp>
#include <kdbhelper.h>
#include <kdblogger.h>

#include <sstream>
#include <string>

// -- Functions ----------------------------------------------------------------------------------------------------------------------------

static int yamlRead (kdb::KeySet & mappings ELEKTRA_UNUSED, kdb::Key & parent)
{
	using namespace kdb;

	YAML::Node config = YAML::LoadFile (parent.getString ());
	std::ostringstream data;
	data << config;

	ELEKTRA_LOG_DEBUG ("Data: “%s”", data.str ().c_str ());

	return ELEKTRA_PLUGIN_STATUS_NO_UPDATE;
}

extern "C" {
using namespace ckdb;

/**
 * @brief This function returns a key set containing the contract of this plugin.
 *
 * @return A contract describing the functionality of this plugin.
 */
static KeySet * contractYamlCpp (void)
{
	return ksNew (30, keyNew ("system/elektra/modules/yamlcpp", KEY_VALUE, "yamlcpp plugin waits for your orders", KEY_END),
		      keyNew ("system/elektra/modules/yamlcpp/exports", KEY_END),
		      keyNew ("system/elektra/modules/yamlcpp/exports/get", KEY_FUNC, elektraYamlcppGet, KEY_END),
		      keyNew ("system/elektra/modules/yamlcpp/exports/set", KEY_FUNC, elektraYamlcppSet, KEY_END),
#include ELEKTRA_README (yamlcpp)
		      keyNew ("system/elektra/modules/yamlcpp/infos/version", KEY_VALUE, PLUGINVERSION, KEY_END), KS_END);
}

// ====================
// = Plugin Interface =
// ====================

/** @see elektraDocGet */
int elektraYamlcppGet (Plugin * handle ELEKTRA_UNUSED, KeySet * returned, Key * parentKey)
{
	if (std::string (keyName (parentKey)) == "system/elektra/modules/yamlcpp")
	{
		KeySet * contract = contractYamlCpp ();
		ksAppend (returned, contract);
		ksDel (contract);

		return ELEKTRA_PLUGIN_STATUS_SUCCESS;
	}

	kdb::Key parent = kdb::Key (parentKey);
	kdb::KeySet keys = kdb::KeySet (returned);

	ELEKTRA_LOG_DEBUG ("Read file “%s”", parent.getString ().c_str ());

	int status = yamlRead (keys, parent);

	parent.release ();
	keys.release ();

	return status;
}

/** @see elektraDocSet */
int elektraYamlcppSet (Plugin * handle ELEKTRA_UNUSED, KeySet * returned ELEKTRA_UNUSED, Key * parentKey ELEKTRA_UNUSED)
{
	return ELEKTRA_PLUGIN_STATUS_NO_UPDATE;
}

Plugin * ELEKTRA_PLUGIN_EXPORT (yamlcpp)
{
	return elektraPluginExport ("yamlcpp", ELEKTRA_PLUGIN_GET, &elektraYamlcppGet, ELEKTRA_PLUGIN_SET, &elektraYamlcppSet,
				    ELEKTRA_PLUGIN_END);
}

} // end extern "C"
