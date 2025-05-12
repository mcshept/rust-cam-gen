# CamGen: Camera Identifier Generator for Rust Players

## Overview

CamGen is a specialized utility designed for Rust players to generate unique and secure camera identifiers. It provides a flexible and user-friendly way to create randomized strings that can be used for camera naming and identification within the game.

## Features

- Generate camera identifiers with custom random string lengths
- Save and reuse configuration for quick identifier generation
- Ensure unique identifiers with a maximum length of 32 characters
- Multiple generation modes to suit different needs

## Installation

### Prerequisites
- C++ Compiler (G++ 8.0 or later)
- C++17 Standard Library Support
- Filesystem Support

### Compilation
Compile the program using the following command:
```bash
g++ -std=c++17 camgen.cpp -o camgen
```

## Usage Modes

### 1. Name with Random String (Saved Configuration)
- Allows adding a custom name prefix to a random string
- Saves the random string length for future use
- Total identifier length limited to 32 characters

**Example:**
```
Enter the length of the random string (max. 32): 10
Enter cam name: MyBase
Generated string: MyBase7Xk9nR2Qm3
```

### 2. Only Random String (Saved Configuration)
- Generates a completely random string
- Saves the random string length for future use
- Total length limited to 32 characters

**Example:**
```
Enter the length of the random string (max. 32): 15
Generated string: 7Xk9nR2Qm3Pt5Lz
```

### 3. Modify Configuration
- Change the saved length for name with random string
- Change the saved length for only random string

**Example:**
```
What would you like to change?
1. Length for name with random string
2. Length for only random string
Your choice: 1
Enter the new length (max. 32): 12
```

### 4. Name with Random String (No Saving)
- Similar to Mode 1, but does not save the configuration
- Asks for string length each time
- Total identifier length limited to 32 characters

### 5. Only Random String (No Saving)
- Similar to Mode 2, but does not save the configuration
- Asks for string length each time
- Total identifier length limited to 32 characters

## Configuration Storage

- Configurations are stored in the `%APPDATA%/CamGen/config.txt` file
- Supports multiple configuration entries
- Persistent across program restarts

## Security Considerations

- Maximum identifier length: 32 characters
- Uses cryptographically secure random number generation
- Supports various naming strategies
- Prevents overly long identifiers

## Rust Integration Tips

1. Use generated identifiers for camera names
2. Ensure uniqueness across your base or server
3. Randomize identifiers to increase security

## Troubleshooting

- Ensure write permissions in the AppData directory
- Check C++ runtime and compiler compatibility
- Verify filesystem support

## Contributing

Contributions are welcome! Please submit pull requests or open issues on the project repository.

## Disclaimer

This tool is a community project and is not officially affiliated with Rust or Facepunch Studios.

## Roadmap and TODO List

### Short-Term Improvements
- [ ] Add command-line argument support for quick generation
- [ ] Implement cross-platform compatibility (Windows, Linux, macOS)
- [ ] Create a configuration export/import feature
- [ ] Add logging functionality for generated identifiers

### Medium-Term Goals
- [ ] Develop a GUI version of the application
- [ ] Create a web-based version for online identifier generation
- [ ] Add support for multiple identifier generation formats
- [ ] Implement a character set customization option

### Long-Term Vision
- [ ] Create plugins/integrations for popular Rust community tools
- [ ] Develop an API for programmatic identifier generation
- [ ] Add advanced security features like collision detection
- [ ] Support for internationalization and localization

### Potential Feature Enhancements
- [ ] Generate identifiers with specific complexity requirements
- [ ] Add a preview mode to show potential identifiers
- [ ] Implement a history tracking system for generated IDs
- [ ] Create export options (CSV, JSON, clipboard)

### Performance and Optimization
- [ ] Benchmark and optimize random string generation
- [ ] Improve configuration file handling
- [ ] Reduce memory footprint
- [ ] Enhance error handling and user feedback

### Community Contributions
- [ ] Set up a contribution guidelines document
- [ ] Create issue and feature request templates
- [ ] Establish a review process for community patches
- [ ] Develop a code of conduct for the project

### Known Limitations to Address
- [ ] Improve error handling for edge cases
- [ ] Add more comprehensive input validation
- [ ] Enhance configuration management
- [ ] Implement better cross-platform file path handling

**Note:** This roadmap is community-driven and subject to change based on user feedback and contributions.
