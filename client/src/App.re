module AppRouter = Router.Create(Route.Config);

module Styles = {
  open Css;
  let app = [
    blue |> color
  ] |> style;
}

[@react.component]
let make = () =>
  <div className={Styles.app}>
    <AppRouter>
      {currentRoute =>
         Route.Config.(
           switch (currentRoute) {
           | Home => <Home />
           | Books => <Books />
           | MyProfile => <MyProfile />
           | NewBook => <NewBook />
           | NotFound => <div> {ReasonReact.string("Not Found")} </div>
           }
         )}
    </AppRouter>
  </div>;
