type book = {
  title: string,
  tag: string,
};

let s = ReasonReact.string;

module Styles = {
  open Css;

  let button = [blue |> borderColor] |> style;
};

module BookRow = {
  [@react.component]
  let make = (~title, ~tag) => <div>
    <span> {title |> s} </span>
    <br />
    <span> {tag |> s} </span>
    </div>;
};

let initialBooks = [{title: "ReasonML 101", tag: "reasonml"}];

module NewBookForm = {
  [@react.component]
  let make = (~addBook) => {
    let (title, setTitle) = React.useState(() => "");
    let (tag, setTag) = React.useState(() => "");
    <>
      <input
        value=title
        type_="text"
        placeholder="title"
        onChange={e => setTitle(e->ReactEvent.Form.target##value)}
      />
      <input
        value=tag
        type_="text"
        placeholder="tags"
        onChange={e => setTag(e->ReactEvent.Form.target##value)}
      />
      <button
        className=Styles.button
        type_="submit"
        onClick={_ => addBook({ title, tag })}>
        {s("Add")}
      </button>
    </>;
  };
};

[@react.component]
let make = () => {
  let (books, setBooks) = React.useState(() => initialBooks);

  <div>
    {books
     |> List.map(b => <BookRow title={b.title} tag={b.tag} />)
     |> Array.of_list
     |> ReasonReact.array}
    <NewBookForm addBook={b => setBooks(bs => [b, ...bs])} />
  </div>;
};
