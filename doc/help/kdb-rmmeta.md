kdb-rmmeta(1) -- Remove metakey of a key from the key database
==============================================================

## SYNOPSIS

`kdb rmmeta <key name> <metaname>`

Where `key name` is the name of the key and `metaname` is the name of the metakey you want to remove.

## DESCRIPTION

This command removes a metakey of a key from the Key database.

## OPTIONS

- `-H`, `--help`:
  Show the man page.
- `-V`, `--version`:
  Print version info.
- `-p`, `--profile <profile>`:
  Use a different kdb profile.
- `-C`, `--color <when>`:
  Print never/auto(default)/always colored output.

## EXAMPLES

To remove metakey `metakey` of a key:
`kdb rmmeta user/example metakey`

## SEE ALSO

- [elektra-metadata(7)](elektra-metadata.md) for an explanation of the metadata concepts.
- [elektra-key-names(7)](elektra-key-names.md) for an explanation of key names.
