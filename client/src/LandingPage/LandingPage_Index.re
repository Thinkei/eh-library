let str = ReasonReact.string;

module Styles = {
  let container = ReactDOMRe.Style.make(~paddingTop="14vw", ());
  let headline =
    ReactDOMRe.Style.make(
      ~maxWidth="24em",
      ~fontWeight="300",
      ~margin="0 auto 2em",
      (),
    );
  let appTitle = ReactDOMRe.Style.make(~fontSize="calc(35.5px + 2vw)", ());
};

[@react.component]
let make = () =>
  <div style=Styles.container>
    <Ehd.Typography.Title level=2 style=Styles.headline>
      {str(
         "Good friends, good books, and a sleepy conscience: this is the ideal life.",
       )}
    </Ehd.Typography.Title>
    <Ehd.Typography.Title level=1 style=Styles.appTitle>
      {str("Employment Hero Bookshelf")}
    </Ehd.Typography.Title>
    <Route.Link route=Route.Config.Books>
      <Ehd.Button> {str("Explore")} </Ehd.Button>
    </Route.Link>
  </div>;
