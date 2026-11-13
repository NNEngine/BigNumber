# Changelog

## [1.1]

### Changed
- Updated the memory ownership model: `Number()` now creates an independent copy of the input string instead of storing the original pointer.
- `BigNumber` instances now own their numeric string representation.
- Added `FreeNumber()` to release the allocated string and structure, ensuring proper memory
management.
