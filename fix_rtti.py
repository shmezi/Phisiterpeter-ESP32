Import("env")

# Remove -frtti from global flags (prevents it hitting .c files)
env.ProcessUnFlags("-frtti")

# Add -frtti specifically to the C++ compiler flags
env.Append(CXXFLAGS=["-frtti"])
