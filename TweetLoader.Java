package brundage;

import com.google.gson.Gson;
import twitter4j.*;
import twitter4j.conf.ConfigurationBuilder;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class TweetLoader {

    private Twitter twitter;

    public TweetLoader() {
        ConfigurationBuilder cb = new ConfigurationBuilder();
        cb.setDebugEnabled(true)
                .setOAuthConsumerKey("qpQ92YcOJ5X3NWKwxz9FF3yGa")
                .setOAuthConsumerSecret("WTE2cSUBDOGf06XeOBu8ItIjJkaQvsUeCNEv3NqttQQ20C0Y9K")
                .setOAuthAccessToken("955930037059960833-0FYIrHTeEZt3QEZU654dv23oyekPYvt")
                .setOAuthAccessTokenSecret("HJrDEmLPS7Pd4LFH46a46sPnW6qNOIOCawuq3syJx6Yih")
                .setJSONStoreEnabled(true);
        TwitterFactory tf = new TwitterFactory(cb.build());
        this.twitter = tf.getInstance();
    }

    public Map<String, BYUITweet> retrieveTweetsWithHashTag(String hashtag){
        Gson gson = new Gson();
        Map<String, BYUITweet> map = new HashMap<String, BYUITweet>();
        List<Status> list = new ArrayList<Status>();
        Query query = new Query(hashtag);
        QueryResult result;
        try {
            result = twitter.search(query);
            list = result.getTweets();
        } catch (TwitterException e) {
            e.printStackTrace();
        }

        for (Status status : list){
            String tweet = TwitterObjectFactory.getRawJSON(status);
            BYUITweet BTweet = gson.fromJson(tweet, BYUITweet.class);
            map.put(BTweet.getUser().getName(), BTweet);
        }
        return map;
    }
}
