module type Config = {
  type route;

  let toUrl: route => string;
  let toRoute: ReasonReact.Router.url => route;
};

module Config = {
  type route =
    | Home
    | Books
    | NewBook
    | MyProfile
    | Shipper
    | NotFound;

  let toRoute = (url: ReasonReact.Router.url) => {
    let hashes = url.hash |> Js.String.split("/") |> Array.to_list;
    switch (url.path) {
    | [""]
    | []
    | ["/"] =>
      switch (hashes) {
      | [""] => Home
      | ["", "books"] => Books
      | ["", "my-profile"] => MyProfile
      | ["", "new-book"] => NewBook
      | ["", "shipper"] => Shipper
      | _ => NotFound
      }
    | _ => NotFound
    };
  };

  let toUrl =
    fun
    | Home => "#"
    | Books => "#/books"
    | MyProfile => "#/my-profile"
    | NewBook => "#/new-book"
    | Shipper => "#/shipper"
    | NotFound => "#/404";
};

module Link = {
  [@react.component]
  let make = (~route, ~style=?, ~children) => {
    let href = Config.toUrl(route);
    let onClick = e => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReact.Router.push(href);
    };
    <a href onClick ?style> children </a>;
  };
};
