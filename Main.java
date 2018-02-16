package brundage;

import javax.swing.text.html.HTMLDocument;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Main {

    public static void main(String[] args) {

        TweetLoader loader = new TweetLoader();
        Map<String, BYUITweet> tweets;

        tweets = loader.retrieveTweetsWithHashTag("BYUI");

        Iterator it = tweets.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry pair = (Map.Entry) it.next();
            BYUITweet user = (BYUITweet) pair.getValue();
            String followers = String.valueOf(user.getUser().getFollowers());
            String message = user.getText();
            System.out.println(pair.getKey() + " (" + followers + " Followers) - " + message);
            it.remove();
        }

    }
}
