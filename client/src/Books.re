include Book;
include AddNewBookForm;

let book1 = {
  title: "Exploring ReasonML and functional programming",
  tags: ["frontend", "ocaml"],
  previewImage: "http://bit.ly/2XMWrE7",
};
let book2 = {
  title: "Learn Web Development with Rails",
  tags: ["backend", "ruby", "rails"],
  previewImage: "http://bit.ly/2y1hmEl",
};
let book3 = {
  title: "The Rust Programming Language",
  tags: ["backend", "ownership"],
  previewImage: "http://bit.ly/2LozvnU",
};
let initialBooks = [book1, book2, book3];

module Styles = {
  open Css;

  let container = style([padding(px(100)), color(black)]);
};

[@react.component]
let make = () => {
  let (books, setBooks) = React.useState(() => initialBooks);

  <div className=Styles.container>
    {books
     |> List.map(book =>
          <Book
            key={book.title}
            title={book.title}
            tags={book.tags}
            previewImage={book.previewImage}
          />
        )
     |> Array.of_list
     |> ReasonReact.array}
     <AddNewBookForm />
  </div>;
};
