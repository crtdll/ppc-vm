mflr %r12
stw %r12, -0x8(%r1)
stwu %r1, -0x30(%r1)

li %r3, 0x48          # "H"
stb %r3, 0x00(%r1)

li %r3, 0x65          # "e"
stb %r3, 0x01(%r1)

li %r3, 0x79          # "y"
stb %r3, 0x02(%r1)

li %r3, 0x20          # " "
stb %r3, 0x03(%r1)

li %r3, 0x66          # "f"
stb %r3, 0x04(%r1)

li %r3, 0x72          # "r"
stb %r3, 0x05(%r1)

li %r3, 0x6F          # "o"
stb %r3, 0x06(%r1)

li %r3, 0x6D          # "m"
stb %r3, 0x07(%r1)

li %r3, 0x20          # " "
stb %r3, 0x08(%r1)

li %r3, 0x50          # "P"
stb %r3, 0x09(%r1)

li %r3, 0x50          # "P"
stb %r3, 0x0A(%r1)

li %r3, 0x43          # "C"
stb %r3, 0x0B(%r1)

li %r3, 0x20          # " "
stb %r3, 0x0C(%r1)

li %r3, 0x70          # "p"
stb %r3, 0x0D(%r1)

li %r3, 0x61          # "a"
stb %r3, 0x0E(%r1)

li %r3, 0x79          # "y"
stb %r3, 0x0F(%r1)

li %r3, 0x6C          # "l"
stb %r3, 0x10(%r1)

li %r3, 0x6F          # "o"
stb %r3, 0x11(%r1)

li %r3, 0x61          # "a"
stb %r3, 0x12(%r1)

li %r3, 0x64          # "d"
stb %r3, 0x13(%r1)

li %r3, 0x20          # " "
stb %r3, 0x14(%r1)

li %r3, 0x70          # "p"
stb %r3, 0x15(%r1)

li %r3, 0x6F          # "o"
stb %r3, 0x16(%r1)

li %r3, 0x67          # "g"
stb %r3, 0x17(%r1)

li %r3, 0x20          # " "
stb %r3, 0x18(%r1)

li %r3, 0x70          # "p"
stb %r3, 0x19(%r1)

li %r3, 0x6F          # "o"
stb %r3, 0x1A(%r1)

li %r3, 0x67          # "g"
stb %r3, 0x1B(%r1)

li %r3, 0x20          # " "
stb %r3, 0x1C(%r1)

li %r3, 0x70          # "p"
stb %r3, 0x1D(%r1)

li %r3, 0x6F          # "o"
stb %r3, 0x1E(%r1)

li %r3, 0x67          # "g"
stb %r3, 0x1F(%r1)

li %r3, 0x21          # "!"
stb %r3, 0x20(%r1)

li %r3, 0x0A          # "\n"
stb %r3, 0x21(%r1)

li %r3, 0x00          # ""
stb %r3, 0x22(%r1)

mr %r3, %r1
li %r0, 0x0
sc

li %r0, 0x1
sc

addi %r3, %r3, 0x200
li %r4, 0x69
li %r5, 0x100
bl 0x18 # memset ram+0x200 to 0x69 (check in debugger)

addi %r1, %r1, 0x30
lwz %r12, -0x8(%r1)
mtlr %r12
blr

# memset
li %r0, 4
sc 
blr