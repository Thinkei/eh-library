module GetBooks = [%graphql
  {|
  query getBooks {
    books {
      id
      title
      image_url
      tags
    }
  }
|}
];

module GetBooksQuery = ReasonApollo.CreateQuery(GetBooks);

module BookTile = NewBooks_BookTile;

[@react.component]
let make = () =>
  <div>
    <GetBooksQuery>
      {({result}) =>
         switch (result) {
         | Loading => <div> {ReasonReact.string("Loading")} </div>
         | Error(error) => <div> {ReasonReact.string(error##message)} </div>
         | Data(response) =>
           <Ehd.Row>
             {/* Handles a deeply nested optional response */
              response##books
              |> Array.map(book =>
                   <BookTile
                     key={string_of_int(book##id)}
                     title=book##title
                     imageUrl=book##image_url
                     tags=book##tags
                   />
                 )
              |> ReasonReact.array}
           </Ehd.Row>
         }}
    </GetBooksQuery>
  </div>;
