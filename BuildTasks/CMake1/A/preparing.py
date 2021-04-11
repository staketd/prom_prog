f = open('A/index.hpp', 'w')
f.write("""class A {
public:
static int foo() {
return 2;
}
};""")
f.close()