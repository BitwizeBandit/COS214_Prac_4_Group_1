TaskForge — Movie Studio Edition

COS 214 Practical 4 — a work-processing system for a movie studio,
demonstrating the Composite, Iterator, State, and Decorator design
patterns working together as one system.

All tools needed to build, run, and debug this project (g++, make, gdb,
valgrind) are provided inside the supplied Docker image — nothing needs
to be installed on the host machine beyond Docker itself.

## Build and run

```
docker build -t taskforge .
docker run -it -v "$(pwd):/taskforge" taskforge bash
```

Inside the container:

```
cd /taskforge
make -k
./taskforge
```

## Submission mode

`src/main.cpp` contains a `DEMO_MODE` flag near the top of the file:

```cpp
#define DEMO_MODE 0
```

- `0` — quiet, fully deterministic, never blocks on stdin (this is the
  mode this submission is built in).
- `1` — adds section banners and interactive pauses between scenarios,
  used only for the live demo presentation.

## Debugging with GDB

```
gdb ./taskforge
(gdb) break <ClassName>::<methodName>
(gdb) run
(gdb) print <variableName>
(gdb) next
(gdb) list
(gdb) continue
```

## Memory checking with Valgrind

```
valgrind --leak-check=full --show-leak-kinds=all ./taskforge < /dev/null
```

The `< /dev/null` redirect ensures the run never blocks waiting for
input, regardless of `DEMO_MODE`.

## Project structure

```
include/
  WorkComponent.h, IteratorType.h
  composite/   ProductionUnit.h, Shot.h
  state/       ShotState.h + four concrete states
  decorator/   Decorator.h + three concrete decorators
  iterator/    WorkIterator.h + two concrete iterators
src/           mirrors include/, plus main.cpp
docs/          design documentation and exported diagrams
```

## Design documentation

See `docs/` for the UML class diagram, object diagram, state diagram,
the three Activity Diagrams, and the full design/ownership rationale.