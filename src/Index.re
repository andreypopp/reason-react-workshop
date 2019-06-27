open Belt;

type status =
  | Active
  | Completed;

type todo = {
  id: int,
  title: string,
  status,
};

type filter =
  | ShowAll
  | ShowActive
  | ShowCompleted;

module Input = {
  [@react.component]
  let make = (~onSubmit) => {
    let (value, setValue) = React.useState(() => "");
    let onChange = ev => {
      let value = ReactEvent.Form.target(ev)##value;
      setValue(_value => value);
    };
    let onKeyDown = ev => {
      switch (ReactEvent.Keyboard.key(ev)) {
      | "Enter" =>
        onSubmit(value);
        setValue(_value => "");
      | _ => ()
      };
    };
    <input
      className="new-todo"
      placeholder="What needs to be done?"
      autoFocus=true
      value
      onChange
      onKeyDown
    />;
  };
};

module FilterButton = {
  [@react.component]
  let make = (~title, ~active, ~onActive) =>
    <a className={active ? "selected" : ""} onClick={_ev => onActive()}>
      {React.string(title)}
    </a>;
};

module Footer = {
  [@react.component]
  let make = (~remaining, ~completed, ~onClearCompleted, ~onFilter, ~filter) =>
    <footer className="footer">
      <span className="todo-count">
        <strong> {React.string(string_of_int(remaining))} </strong>
        {React.string(remaining == 1 ? " item" : " items")}
        {React.string(" left")}
      </span>
      <ul className="filters">
        <li>
          <FilterButton
            title="All"
            active={filter == ShowAll}
            onActive={() => onFilter(ShowAll)}
          />
        </li>
        <li>
          <FilterButton
            title="Active"
            active={filter == ShowActive}
            onActive={() => onFilter(ShowActive)}
          />
        </li>
        <li>
          <FilterButton
            title="Completed"
            active={filter == ShowCompleted}
            onActive={() => onFilter(ShowCompleted)}
          />
        </li>
      </ul>
      {completed > 0
         ? <button
             className="clear-completed" onClick={_ev => onClearCompleted()}>
             {React.string("Clear completed")}
           </button>
         : ReasonReact.null}
    </footer>;
};

module TodoList = {
  [@react.component]
  let make = (~todos, ~onUpdateStatus, ~onRemoveTodo) => {
    let renderTodo = item => {
      let onCompleted = _ev => {
        let nextStatus =
          switch (item.status) {
          | Active => Completed
          | Completed => Active
          };
        onUpdateStatus(item.id, nextStatus);
      };
      <li key={string_of_int(item.id)}>
        <div className="view">
          <input
            className="toggle"
            type_="checkbox"
            checked={item.status == Completed}
            onChange=onCompleted
          />
          <label> {React.string(item.title)} </label>
          <button
            className="destroy"
            onClick={_ev => onRemoveTodo(item.id)}
          />
        </div>
      </li>;
    };
    let items = todos->List.map(renderTodo)->List.toArray;
    <ul className="todo-list"> {React.array(items)} </ul>;
  };
};

module App = {
  type state = {
    todos: list(todo),
    filter,
  };

  type action =
    | AddTodo(string)
    | RemoveTodo(int)
    | UpdateStatus(int, status)
    | UpdateStatusForAll(status)
    | SetFilter(filter)
    | ClearCompleted;

  let onAction = (state, action) =>
    switch (action) {
    | AddTodo(title) =>
      let id = List.length(state.todos);
      let todo = {id, title, status: Active};
      let todos = [todo, ...state.todos];
      {...state, todos};
    | RemoveTodo(id) =>
      let todos =
        state.todos
        ->List.reduce([], (todos, todo) =>
            if (todo.id == id) {
              todos;
            } else {
              [todo, ...todos];
            }
          )
        ->List.reverse;
      {...state, todos};
    | UpdateStatusForAll(status) =>
      let todos = List.map(state.todos, todo => {...todo, status});
      {...state, todos};
    | UpdateStatus(id, status) =>
      let todos =
        List.map(state.todos, todo =>
          if (todo.id == id) {
            {...todo, status};
          } else {
            todo;
          }
        );
      {...state, todos};
    | SetFilter(filter) => {...state, filter}
    | ClearCompleted =>
      let todos = List.keep(state.todos, todo => todo.status == Active);
      {...state, todos};
    };

  [@react.component]
  let make = () => {
    let ({todos, filter}, dispatch) =
      React.useReducer(onAction, {todos: [], filter: ShowAll});

    let onSubmit = text => dispatch(AddTodo(text));
    let onRemoveTodo = id => dispatch(RemoveTodo(id));
    let onUpdateStatus = (id, status) => dispatch(UpdateStatus(id, status));
    let onFilter = filter => dispatch(SetFilter(filter));
    let onClearCompleted = () => dispatch(ClearCompleted);
    let onToggleAll = ev => {
      let checked = ReactEvent.Form.target(ev)##checked;
      dispatch(UpdateStatusForAll(checked ? Completed : Active));
    };

    let (remaining, completed) =
      List.reduce(todos, (0, 0), ((remaining, completed), todo) =>
        switch (todo.status) {
        | Completed => (remaining, completed + 1)
        | Active => (remaining + 1, completed)
        }
      );

    let todos =
      switch (filter) {
      | ShowAll => todos
      | ShowActive => List.keep(todos, todo => todo.status == Active)
      | ShowCompleted =>
        List.keep(todos, todo => todo.status == Completed)
      };

    <section className="todoapp">
      <header className="header">
        <h1> {ReasonReact.string("todos")} </h1>
        <Input onSubmit />
      </header>
      <section className="main">
        <input
          className="toggle-all"
          id="toggle-all"
          type_="checkbox"
          onChange=onToggleAll
        />
        <label htmlFor="toggle-all">
          {ReasonReact.string("Mark all as complete")}
        </label>
        <TodoList todos onUpdateStatus onRemoveTodo />
      </section>
      <Footer
        remaining
        completed
        onFilter
        onClearCompleted
        filter={filter}
      />
    </section>;
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");
