module type Config = {
  type route;

  let toUrl: route => string;
  let toRoute: ReasonReact.Router.url => route;
};

module Config = {
  type route =
    | Home
    | Books
    | MyProfile
    | NotFound;

  let toRoute = (url: ReasonReact.Router.url) => {
    switch (url.path) {
    | [] => Home
    | ["books"] => Books
    | ["my-profile"] => MyProfile
    | _ => NotFound
    };
  };

  let toUrl =
    fun
    | Home => "/"
    | Books => "/books"
    | MyProfile => "/my-profile"
    | NotFound => "/404";
};

module Link = {
  [@react.component]
  let make = (~route, ~children) => {
    let href = Config.toUrl(route);
    let onClick = e => {
      ReactEvent.Mouse.preventDefault(e);
      ReasonReact.Router.push(href);
    };
    <a href onClick> children </a>;
  };
};
